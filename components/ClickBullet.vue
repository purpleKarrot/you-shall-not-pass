<script setup>
defineProps({
    at: { type: Array, default: () => [] },
});
</script>

<template>
    <li
        class="transition-all duration-200"
        :class="{
            'text-gray-400 line-through opacity-40': at.includes($clicks),
        }"
    >
        <slot />
    </li>
</template>
