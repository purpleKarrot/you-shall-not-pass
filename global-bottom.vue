<script setup lang="ts">
import { onMounted, onUnmounted } from 'vue'

const CODE_WRAPPER_SELECTOR = '.slidev-code-wrapper.slidev-code-magic-move'
const CODE_SCROLL_SELECTOR = 'pre.shiki-magic-move-container'
const HIGHLIGHT_SELECTOR = '.highlighted'
const MIN_LINES = 23

function getScrollContainer(wrapper: HTMLElement) {
  const container = wrapper.querySelector(CODE_SCROLL_SELECTOR)
  return container instanceof HTMLElement ? container : null
}

function scrollHighlightedRangeIntoView(container: HTMLElement) {
  // Shiki represents lines as text separated by <br>.
  // Short code blocks should be left completely untouched.
  if (container.querySelectorAll('br').length < MIN_LINES)
    return

  const highlighted = Array.from(container.querySelectorAll(HIGHLIGHT_SELECTOR))
    .filter((element): element is HTMLElement => {
      return element instanceof HTMLElement && element.offsetParent !== null
    })

  if (!highlighted.length)
    return

  const containerRect = container.getBoundingClientRect()

  const top = Math.min(
    ...highlighted.map(element =>
      element.getBoundingClientRect().top -
      containerRect.top +
      container.scrollTop,
    ),
  )

  const bottom = Math.max(
    ...highlighted.map(element =>
      element.getBoundingClientRect().bottom -
      containerRect.top +
      container.scrollTop,
    ),
  )

  const center = (top + bottom) / 2

  const targetTop =
    center -
    container.clientHeight / 2

  const maxScrollTop =
    Math.max(0, container.scrollHeight - container.clientHeight)

  const scrollTop = Math.max(
    0,
    Math.min(targetTop, maxScrollTop),
  )

  if (Math.abs(container.scrollTop - scrollTop) < 2)
    return

  container.scrollTo({
    top: Math.round(scrollTop),
    behavior: 'smooth',
  })
}

function updateCodeBlocks() {
  const slideContent = document.getElementById('slide-content')

  if (!(slideContent instanceof HTMLElement))
    return

  const wrappers = Array.from(
    slideContent.querySelectorAll(CODE_WRAPPER_SELECTOR),
  )

  for (const wrapper of wrappers) {
    if (!(wrapper instanceof HTMLElement))
      continue

    const container = getScrollContainer(wrapper)

    if (!container)
      continue

    scrollHighlightedRangeIntoView(container)
  }
}

let frame = 0
let bodyObserver: MutationObserver | null = null
let slideObserver: MutationObserver | null = null

function scheduleUpdate() {
  cancelAnimationFrame(frame)

  frame = requestAnimationFrame(() => {
    frame = requestAnimationFrame(updateCodeBlocks)
  })
}

onMounted(() => {
  const observeSlideContent = () => {
    const slideContent = document.getElementById('slide-content')

    if (!(slideContent instanceof HTMLElement))
      return false

    slideObserver?.disconnect()

    slideObserver = new MutationObserver(scheduleUpdate)

    slideObserver.observe(slideContent, {
      subtree: true,
      childList: true,
    })

    return true
  }

  if (!observeSlideContent()) {
    bodyObserver = new MutationObserver(() => {
      if (observeSlideContent()) {
        bodyObserver?.disconnect()
        bodyObserver = null
        scheduleUpdate()
      }
    })

    bodyObserver.observe(document.body, {
      subtree: true,
      childList: true,
    })
  }

  window.addEventListener('resize', scheduleUpdate, { passive: true })

  scheduleUpdate()
})

onUnmounted(() => {
  cancelAnimationFrame(frame)

  window.removeEventListener('resize', scheduleUpdate)

  bodyObserver?.disconnect()
  slideObserver?.disconnect()
})
</script>

<template>
  <div hidden aria-hidden="true" />
</template>
